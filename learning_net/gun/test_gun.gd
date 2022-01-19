extends "res://learning_net/gun/base_gun.gd"

#nueron lib
onready var brain = preload('res://lib_godot/NueronScript.gdns').new()

func _ready() -> void:
	# input layer target (posX,posY,targetSpeed,targetCourse)
	# all normalize from 0 to 1
	brain.addLayer(4)
	#hidden layers
	brain.addLayer(5)
	brain.addLayer(5)
	# output rotation on tagert
	brain.addLayer(1)
	brain.startNueralNetController()

func input_layer(data:Array)->void:
	var x = range_lerp( data[0], 0, screen_size.x, 0, 1 )
	var y = range_lerp( data[1], 0, screen_size.y, 0, 1 )
	var sp = range_lerp( data[2], 0, 500, 0, 1 )
	var co = range_lerp( data[3], -3, 3, 0, 1 )
	var control:Array = [ x, y, sp, co ]
	brain.setData(control,len(control),0)
	brain.forWards()
	shoot()



func shoot() -> void:
	var rot = brain.getLayer(3)[0][0]
	$gun.rotation = range_lerp(rot,0,1,-3, 3)
	emit_signal("shoot",Bullet,Muzzle.global_position,$gun.rotation)
	$LaserSound.play()
