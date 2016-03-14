<?php

	global $files_changed;
	$files_changed = false;
	global $CC, $CXX;
	$CC = "gcc";
	$CXX = "g++";

	/**
	 * Main entry point for the build script
	 * $build_dir - The directory to dump all of our objects into.
	 */
	function bob_build($args, $build_dir="build")
	{
		create_constant("BUILD_DIR", get_real_path($build_dir));

		check_build_dir();

		$target = isset($args[1]) ? "target_" . $args[1] : "target_default"; // Find target and if none were specified in arguments use default

		if (!function_exists($target)) { // Validate that our build target is here
			log_error("$target was not found!");
		}

		$target(); // Launch our target
	}

	/**
	 * Make sure the directory in BUILD_DIR can be used
	 */
	function check_build_dir()
	{
		if (!defined("BUILD_DIR"))
		{
			log_error("BUILD_DIR constant was not set before entering check_build_dir()");
		}

		if (!file_exists(BUILD_DIR))
		{
			mkdir(BUILD_DIR);
		}

		if (!is_writable(BUILD_DIR))
		{
			log_error("Cannot write to build directory! Check file permissions!");
		}

		if (!is_readable(BUILD_DIR))
		{
			log_error("Cannot read from build directory! Check file permissions!");
		}
	}

	/**
	 * Check to see if a file has changed.
	 * $file - The file you are inspecting
	 * $time - The time you think it was last changed
	 */
	function has_file_changed($file, $time)
	{
		return filemtime($file) != $time; // mtime != time == has changed
	}

	/**
	 * Link all of the object files within the BUILD_DIR.
	 * Checks to see if the linkage process is needed before linking is started.
	 *
	 * $linker - Linker command to use. Most common will most likely be ld
	 * $output - The output file to make
	 * $flags - command flags to use
	 */
	function link_all($linker, $output, $flags)
	{
		global $files_changed; // Files that have been compiled during lifetime
		if (file_exists($output) && !$files_changed) // If the output does not exist and...
		{					 // if we ahve compiled nothing
			log_info("Link was unneeded. No changes made"); // Nothing needed
		}
		else
		{
			log_info("Starting link step");

			$objects = sanitize_file_arguments(get_all_objects());

			log_exec("$linker $flags -o $output $objects"); // Execute and log command
		}
	}

	/**
	 * Sanitize file paths for use in a command
	 * $files  - An array of files that will be sanitized
	 * returns - Returns a string, delimited by spaces, with the path names surrounded by quote marks (")
	 */
	function sanitize_file_arguments($files)
	{
		$sanatized = ""; // Used to allow spaces in path names
		foreach ($files as $file) // Find all of our object files
		{
			$sanatized .= "\"$file\" "; // Put them into a joined list
		}
		return trim($sanatized);
	}

	/**
	 * Get all of the object files from the build directory
	 * returns - All built object files
	 */
	function get_all_objects()
	{
		return glob(BUILD_DIR . "*.o");
	}

	/**
	 * Compile a file into object files.
	 * $source_file     - The file that we want to compile
	 * returns - The file that was created during the compile.
	 */
	function compile($compiler, $flags, $source_file)
	{
		$output_file = get_object_name($source_file); // Get the object name
		$source_time = filemtime($source_file); // Source file last modified

		if (file_exists($output_file) && !has_file_changed($output_file, $source_time)) // Should we compile the code?
		{
			return null;
		}

		log_info("Compiling $source_file -> $output_file");
		log_exec("$compiler $flags -o $output_file $source_file");

		if (file_exists($output_file))
		{
			touch($output_file, $source_time); // Set modified time to that of the source. Dont mess with IDEs and allow us to tell if we need to compile
		}
		else
		{
			log_error("Compiling of $source_file failed!");
		}

		return $output_file;
	}

	/**
	 * Compile all files matching a pattern.
	 * $dir             - Directory containing source
	 * $ext             - Extension of the source file
	 * $recursive       - Should the directory search be recursive?
	 * $compile_command - Command used to compile source
	 */
	function compile_all($dir, $ext, $recursive, $compiler, $flags)
	{
		global $files_changed;
		$pattern = get_real_path($dir) . "*." . $ext;
		$files = $recursive ? glob_recursive($pattern) : glob($pattern); // Find files

		log_info("Matching all files to $pattern");

		foreach ($files as $file)
		{
			$of = compile($compiler, $flags, $file); // Compile file
			if (!is_null($of)) // Everything is ok
			{
				$files_changed = true;
			}
		}
	}

	/**
	 * Get a path to a folder.
	 * A DIRECTORY_SEPARATOR is appended to the end.
	 * $path - The path to be sanitized
	 * returns - Sanatized path name
	 */
	function get_real_path($path)
	{
		return realpath($path) . DIRECTORY_SEPARATOR;
	}

	/**
	 * Get the predicted name of the object file that will be created by a compile_command
	 * $file - Source file
	 * returns - Path to the file
	 */
	function get_object_name($file)
	{
		return get_real_path(BUILD_DIR) . basename($file) . ".o";
	}

	/**
	 * Create a a constant
	 * $name  - Name of the constant you want to assign
	 * $val   - The default value of the constant
	 * $force - If the constant should be set if it exists. Defaults to false
	 */
	function create_constant($name, $val, $force = false)
	{
		if ($force || !defined($name))
		{
			define($name, $val);
		}
	}

	/**
	 * Get the date in a human readable format.
	 * returns - Year-Month-Day Hours:Min:Sec
	 */
	function get_date()
	{
		return date("Y-m-d H:i:s");
	}

	/**
	 * Log a message to the console
	 * Format and log a message
	 * $level   - The level of this log
	 * $message - The message we want to log
	 * $die     - If the message should be emitted with a die or echo. Defaults to false
	 *   		  If true, the application will exit.
	 */
	function log_message($level, $message, $die=false)
	{

		if (is_array($message))
		{
			foreach ($message as $line)
			{
				log_message($level, $line);
			}
		}
		else
		{
			$date = get_date();
			echo "[$date] [$level] $message\r\n";
		}

		if ($die)
		{
			die(); // Kill script if needed
		}

	}

	/**
	 * Log an info message to the console
	 * $message - The message to output.
	 */
	function log_info($message)
	{
		log_message("info", $message);
	}

	/**
	 * Log a fatal error to the console.
	 * This will exit the application
	 * $message - The message to output.
	 */
	function log_error($message)
	{
		log_message("error", $message, true);
	}

	/**
	 * Execute a command and log it's execution
	 * $command - Terminal commmand to run log
	 */
	function log_exec($command)
	{
		$output = array();
		$return_var = 0;

		log_message("command", "Executing ($command)");

		exec($command, $output, $return_var);

		log_message("command", $output); // Foward STD out to the user

		return $return_var;
	}

	// Does not support flag GLOB_BRACE
	function glob_recursive($pattern, $flags = 0)
	{
		$files = glob($pattern, $flags);
		foreach (glob(dirname($pattern).'/*', GLOB_ONLYDIR|GLOB_NOSORT) as $dir) {
			$files = array_merge($files, glob_recursive($dir.'/'.basename($pattern), $flags));
		}
		return $files;
	}
?>
