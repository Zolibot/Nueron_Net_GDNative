extends Area2D

signal in_position

export (int) var speed = 500
var velocity = Vector2()
var target
var last_distance = 0

var start_pos:Vector2
var start_target_speed:int
var gun_rotation:float
var data:Array

var count:int

func start(pos, dir):
	start_pos = target.get_position()
	start_target_speed = target.get_speed()
	count = target.get_count()

	gun_rotation = dir
	data = [ start_pos.x, start_pos.y,
			start_target_speed,
			target.velocity.angle(),
			gun_rotation ]
	position = pos
	velocity = Vector2(speed,0).rotated(dir)
	rotation = dir

func _process(delta):
	position += velocity * delta

func _on_VisibilityNotifier2D_screen_exited():
	queue_free()

func _on_Bullet_area_entered(area: Area2D) -> void:
	if area.is_in_group("target") and count == area.get_count():
		emit_signal('in_position', data)
		$Explow/AnimationPlayer.play('boom')
		yield($Explow/AnimationPlayer,'animation_finished')
		queue_free()
