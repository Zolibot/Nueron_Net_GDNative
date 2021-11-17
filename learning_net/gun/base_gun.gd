extends Sprite

signal shoot

export (PackedScene) var Bullet

onready var Muzzle = $gun/Position2D
onready var tween = $Tween


onready var screen_size = get_viewport().size


func _process(delta: float) -> void:
	$aim.look_at(get_global_mouse_position())

