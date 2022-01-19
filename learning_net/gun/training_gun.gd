extends "res://learning_net/gun/base_gun.gd"




func shoot() -> void:
	$gun.rotation = $aim.get_rotation()
	emit_signal("shoot",Bullet,Muzzle.global_position,$gun.rotation)
	$LaserSound.play()


func _input(event: InputEvent) -> void:
	if event is InputEventMouseButton:
		shoot()
