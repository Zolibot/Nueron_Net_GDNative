extends Control


var scene_path_to_load

var dic:Dictionary = {traning_net='res://learning_net/traning_net.tscn',
				test_nueron_net='res://learning_net/test_nueron_net.tscn'}


func _ready():
	set_process(true)
	$"VBoxContainer".grab_focus()
	for button in $"VBoxContainer".get_children():
		button.connect("pressed", self, "_on_Button_pressed", [button.text])

func _on_Button_pressed(scene_to_load):
	scene_path_to_load = dic[scene_to_load]
	$UISound.play()
	$FadeIn.show()
	$FadeIn.fade_in()

func _on_FadeIn_fade_finished():
# warning-ignore:return_value_discarded
	get_tree().change_scene(scene_path_to_load)


func _on_exit_pressed() -> void:
	get_tree().quit()
