extends Area2D

export (int) var speed:int = 300 setget set_speed, get_speed
var velocity = Vector2()
var start:Vector2
var count:int = 0 setget _set_count, get_count


func _set_count(c:int)->void:
	count = c

func get_count()->int:
	return count

func set_speed(sp:int)->void:
	speed = sp

func get_speed()->int:
	return speed

func start(pos, dir):
	position = pos
	start = pos
	velocity = Vector2(speed,0).rotated(dir)
	rotation = dir

func _process(delta):
	position += velocity * delta

func _on_VisibilityNotifier2D_viewport_exited(viewport: Viewport) -> void:
	position = Vector2(1,rand_range(viewport.size.y-300,0))
	speed = rand_range(200,600)
	velocity = Vector2(speed,0).rotated(rand_range(-0.2,0.2))
	count+=1
	#queue_free()
