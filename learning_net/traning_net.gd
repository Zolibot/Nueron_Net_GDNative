extends Node2D


onready var statistic_algo:Label = $CanvasLayer/MarginContainer2/Label
onready var base_gun = $traning_gun
onready var screen_size = get_viewport().size

var learning_data:Array


func _ready() -> void:
	$target.start(Vector2(0,300),0)
	pass
	
func _process(delta: float) -> void:
	statistic_algo.set_text(diplay_statistic())

func diplay_statistic()->String:
	var best = " ANGLE:   "
	best+= str(base_gun.position.angle_to_point(get_global_mouse_position()))+"\n"
	var pos:Vector2 = get_global_mouse_position()
	best+= " POSITION: \n x:" + str(pos.x)+"\n y:"+str(pos.y)+"\n"
	best+= " DATA SIZE: "+ str(len(learning_data))
	return best

func save_data(data:Array)->void:
	var pos:Vector2 = Vector2(data[0],data[1])
	var speed:float = data[2]
	var course:float = data[3]
	var rotat:float = data[4]

	var x = range_lerp(pos.x, 0, screen_size.x, 0,1 )
	var y = range_lerp( pos.y, 0, screen_size.y, 0, 1 )
	var sp = range_lerp( speed, 0, 500, 0, 1 )
	var co = range_lerp( course, -3, 3, 0, 1 )
	var rot = range_lerp( rotat, -3, 3, 0, 1 )
	var control:Array = [ x, y, sp, co, rot ]
	
	learning_data.append(control)


func _on_exit_pressed() -> void:
	get_tree().change_scene('res://learning_net/main.tscn')
	

func _on_save_pressed() -> void:
	var file:File = File.new()
	file.open("user://learning_data.sava",File.WRITE)
	file.store_var(learning_data)
	file.close()
	
	$CanvasLayer/info/Label.set_text("the training data is saved")
	$AnimationPlayer.play('New Anim')
	
	print(learning_data)

func _on_base_gun_shoot( bullet, pos, dir ) -> void:
	var b = bullet.instance()
	b.target = $target
	b.start(pos,dir)
	b.connect('in_position',self,'save_data')
	add_child(b)
