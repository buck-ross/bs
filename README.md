# BS
The BrainFuck Shell.

```bash
echo "++++++++[>++++[>++>+++>+++>+<<<<-]>+>->+>>+[<]<-]>>.>>---.+++++++..+++.>.<<-.>.+++.------.--------.>+.>++." | bs
```

## Usage
BS is primarily designed as a stream-manipulator. By default, both code and input data are read sequentially from standard in, and all output is directed toward standard out. For example, `echo ",a." | bs` will cause "a" to be printed to standard out.

Input and output can also be redirected to files be passing the file names as CLI arguments in the following format:
> bs &lt;program file&gt; &lt;input file&gt; &lt;output file&gt;

For example, calling `bs ./prog.txt ./input.txt ./output.txt` will execute the BrainFuck program in "prog.txt", read input data from "input.txt", and output data into "output.txt".

Additionally, the user may choose to only pass the program file or only the program and input files. For example, if "prog.txt" contains the code `,>+++[<.>-]`, then the call `echo "a" | bs ./prog.txt` will print "aaa" to standard out.

## Building from Source
1. Download the latest source tarball: `wget https://github.com/haximilian/bs/releases/download/v1.0.0/brainfuck-shell.1.0.0.tar.gz`
2. Unpack the source code: `tar xzvf brainfuck-shell.*.tar.gz`
3. Enter the build directory: `cd brainfuck-shell/build`
4. Configure the build environment: `../configure`
5. ***(optional)*** If you intend to modify the source code, it's recommended that you configure the debug build with `../configure --enable-debug`.
6. Run the build script: `make`
7. Make sure everything works the way it's supposed to: `make check`
8. ***(optional)*** Install the package: `sudo make install`
9. ***(optional)*** Check that the installation was successful: `make installcheck`


# [<img src="http://www.wtfpl.net/wp-content/uploads/2012/12/logo-220x1601.png" width="50">](https://www.wtfpl.net) License
Copyright &copy; 2018 Haximilian<br/>
**This project is licensed under The [Do What The Fuck You Want To Public License](http://www.wtfpl.net/txt/copying/).**<br>
For a complete copy of the license, please see the included "LICENSE.txt" file.

