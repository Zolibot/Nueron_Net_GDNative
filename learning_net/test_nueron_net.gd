extends Node2D


onready var statistic_algo:Label = $CanvasLayer/MarginContainer2/Label
onready var base_gun = $test_gun
onready var info = $CanvasLayer/info/Label
onready var screen_size = get_viewport().size
onready var file_dilog:FileDialog = FileDialog.new()


var learning_data:Array
var count = 0
var flag:bool = false

var is_connected = false


var rand

func _ready() -> void:
	$CanvasLayer/Dialog.add_child(file_dilog)
	$CanvasLayer/info.visible = false
	$target.start(Vector2(0,300),0)
	pass

func _process(delta: float) -> void:
	#$target.set_position(get_global_mouse_position())
	statistic_algo.set_text(diplay_statistic())


func diplay_statistic()->String:
	var best = " ANGLE:   "
	best+= str(base_gun.position.angle_to_point(get_global_mouse_position()))+"\n"
	var pos:Vector2 = get_global_mouse_position()
	best+= " POSITION: \n x:" + str(pos.x)+"\n y:"+str(pos.y)+"\n"
	best+= " DATA SIZE: "+ str(len(learning_data))
	return best


func can_shoot():
	base_gun.input_layer([$target.position.x,$target.position.y,
		$target.get_speed(),
		$target.velocity.angle()])


func _input(event: InputEvent) -> void:
	if event is InputEventMouseButton and event.pressed:
		can_shoot()


func _on_test_gun_shoot( bullet, pos, dir ) -> void:
	var b = bullet.instance()
	b.target = $target
	b.start(pos,dir)
	#b.connect('in_position',self,'save_data')
	add_child(b)

func _on_exit_pressed() -> void:
	get_tree().change_scene('res://learning_net/main.tscn')
	pass # Replace with function body.



func _on_traning_pressed() -> void:
	file_dilog.set_margins_preset(Control.PRESET_WIDE,Control.PRESET_MODE_KEEP_SIZE)
	file_dilog.window_title = "Select training data"
	file_dilog.margin_top = 100
	file_dilog.margin_left = 400
	file_dilog.set_mode(FileDialog.MODE_OPEN_FILE)
	file_dilog.set_access(FileDialog.ACCESS_USERDATA)
	file_dilog.set_current_dir("user://")
	file_dilog.set_current_path("user://")
	file_dilog.visible = true
	file_dilog.set_filters(PoolStringArray(["*.sava ; the training data"]))
	file_dilog.invalidate()
	if not is_connected:
		file_dilog.connect('file_selected',self,'traning')
		is_connected = true


func traning(path)->void:
	print(path)
	var file:File = File.new()
	file.open(path,File.READ)
	var learning_dat = file.get_var()
	file.close()
	info.set_text("start traning")
#	$AnimationPlayer.play('New Anim')
	while true:
		rand = rand_range(0,len(learning_dat)-1)
		var x = learning_dat[rand][0]
		var y = learning_dat[rand][1]
		var s = learning_dat[rand][2]
		var c = learning_dat[rand][3]
		var list:Array = [x,y,s,c]
		base_gun.brain.setData(list,len(list),0)
		base_gun.brain.learns([learning_dat[rand][4]])
		count+=1
		if count%10000 == 0:
			print(base_gun.brain.getError(), " count:", count)
		if count == 200000:
			count = 0
			break
	info.set_text("traning is over")
	$AnimationPlayer.play('New Anim')
	print("traning is over")

func _on_save_pressed() -> void:
	set_process(false)
	print("____________________________")
	var t=0
	var d = base_gun.brain.saveNueralNetControllerState()

	var file:File = File.new()
	file.open("user://weight.wi",File.WRITE)
	if file.is_open():
		for x in d:
			file.store_line(x)

	file.close()
	info.set_text("weights is save")
	$AnimationPlayer.play('New Anim')



func _on_load_weights_pressed() -> void:
	file_dilog.set_margins_preset(Control.PRESET_WIDE,Control.PRESET_MODE_KEEP_SIZE)
	file_dilog.margin_top = 100
	file_dilog.margin_left = 400
	file_dilog.window_title = "Select nueron weights"
	file_dilog.set_mode(FileDialog.MODE_OPEN_FILE)
	file_dilog.set_access(FileDialog.ACCESS_USERDATA)
	file_dilog.set_current_dir("user://")
	file_dilog.set_current_path("user://")
	file_dilog.visible = true
	file_dilog.set_filters(PoolStringArray(["*.wi ; Weight NueronNet"]))
	file_dilog.invalidate()
	file_dilog.connect('file_selected',self,'load_weights')

func load_weights(path)->void:
	print(path)
	var n_weights:File = File.new()
	n_weights.open(path,File.READ)

	var ss:String = n_weights.get_as_text()
	n_weights.close()
	var ddd = ss.split("\n")
	print(ddd)

	var pool:PoolStringArray = PoolStringArray()

	for x in ddd:
		pool.append(x)

	var brain1 = load('res://lib_godot/NueronScript.gdns').new()
	brain1.loadNueralNetControllerState(pool)
	base_gun.brain = brain1
	info.set_text("new brain weights loaded")
	$AnimationPlayer.play('New Anim')
	print("new brain weights loaded")


func _on_Timer_timeout() -> void:
	can_shoot()
