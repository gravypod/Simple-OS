
<?php
	define("KERNEL_DIR", "./kernel/");
	date_default_timezone_set('America/New_York');

	require_once 'bob.php';

	bob_build($argv);

	function target_default() // Default target that will execute.
	{
		target_compile();
		target_run();
	}

	function target_compile($debug=false) // Compile target, compiles any updated files, links if changes are made
	{
		$CXX_ARGS = "-std=c99 -ffreestanding -nostdlib -static -nostdinc -fno-stack-protector -I includes -m32 -c";
		if ($debug) {
			$CXX_ARGS = $CXX_ARGS . " -g";
		}
		compile_all(KERNEL_DIR, "c", true, "gcc", $CXX_ARGS);
		compile_all(KERNEL_DIR, "asm", true, "nasm", "-f elf");

		link_all("ld", "kernel.bin", "-m elf_i386 -T link.ld");
	}

	function target_debug() 
	{
		target_compile(true);
		log_info("To begin debugging run \"$./debug_qemu.sh\"");
	}

	function target_run() // Attempts to run the kernel in the VM
	{
		log_info("Attempting to start the kernel");
		log_exec("qemu-system-i386 -kernel kernel.bin");
	}
?>
