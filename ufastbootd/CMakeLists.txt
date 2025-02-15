add_executable(ufastbootd
	commands/buffer.c
	commands/file.c
	commands/flash.c
	commands/reboot.c
	commands/utils.c
	commands/variable.c
	blocks.c
	command.c
	constructor.c
	fastboot.c
	sparse.c
	variable.c
	list.c
	lib.c
	debug.c
	main.c
)

target_link_libraries(ufastbootd PRIVATE
	pthread
	blkid
)
