extends Node2D


onready var brain = preload('res://lib_godot/NueronScript.gdns').new()
var control = [0.0, 0.3, 1.0, 0.1, 1.0, 0.0]
var answer = [1.0, 0.0, 1.0, 0.0]


func _ready() -> void:
	brain.addLayer(6)
	brain.addLayer(10)
	brain.addLayer(4)
	brain.startNueralNetController()

func _process(delta: float) -> void:
	brain.setData(control,len(control),0)
	brain.learns(answer)
	print(brain.getError())
	OS.set_window_title(str(Engine.get_frames_per_second()))


func _on_Button_pressed() -> void:
	set_process(false)
	print("____________________________")
	var t=0
	var d = brain.saveNueralNetControllerState()
	for x in brain.saveNueralNetControllerState():
		print(t," ",typeof(x))
		t+=1

	var file:File = File.new()
	file.open("user://weight.wi",File.WRITE)
	if file.is_open():
		for x in d:
			file.store_line(x)

	file.close()

	$FileDialog.set_mode(FileDialog.MODE_OPEN_FILE)
	$FileDialog.visible = true
	$FileDialog.set_filters(PoolStringArray(["*.wi ; Weight NueronNet"]))
	$FileDialog.invalidate()



func _on_FileDialog_confirmed() -> void:
	var n_weights:File = File.new()
	n_weights.open($FileDialog.get_current_path(),File.READ)

	var ss:String = n_weights.get_as_text()
	n_weights.close()
	var ddd = ss.split("\n")
	print(ddd)

	var pool:PoolStringArray = PoolStringArray()

	for x in ddd:
		pool.append(x)

	for x in pool:
		print(x," ",typeof(x))

	var brain1 = load('res://lib_godot/NueronScript.gdns').new()
	brain1.loadNueralNetControllerState(pool)
	brain = brain1
	set_process(true)
