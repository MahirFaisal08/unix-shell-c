# UNIX Shell in C  
![Language](https://img.shields.io/badge/language-C-blue)  
![License](https://img.shields.io/badge/license-MIT-green)  
![Status](https://img.shields.io/badge/status-active-success)  

This is a simple **UNIX-like shell** implemented in C. 
The shell supports running Linux commands, I/O redirection, piping, command history, and signal handling.  

---

## Features  
1. Display a shell prompt (`sh>`) and read user input  
2. Execute Linux system commands using `fork` and `exec`  
3. Input (`<`) and output (`>`, `>>`) redirection  
4. Command piping (`|`) – supports multiple pipes  
5. Multiple commands in-line separated by (`;`)  
6. Multiple commands in sequence using (`&&`)  
7. Command history support (`history` command)  
8. Signal handling – pressing **`Ctrl+C`** won’t terminate the shell, only the running process  

---

## Compilation & Run  

1. **Command for Clone the repository**  
   ```bash
   git clone https://github.com/MahirFaisal08/unix-shell-c.git
   cd unix-shell-c
   

2. **Command for Compile the shell**
   ```bash
   gcc unix-shell-c.c -o mysh

   
3. **Command for Run the shell**
   ```bash
   ./mysh
---
## Example Usage
sh> pwd
/home/user/projects

sh> ls -l > files.txt

sh> cat files.txt | grep ".c"

sh> echo "Hello" >> output.txt

sh> history
1. pwd
2. ls -l > files.txt
3. cat files.txt | grep ".c"
4. echo "Hello" >> output.txt
---
## Project Specs
- Basic shell functionality & built-in command support  
- Input/output redirection (`<`, `>`, `>>`)  
- Command piping (`|`)  
- Signal handling (`Ctrl+C`)  
- Logical operators (`;`, `&&`)  
- Command history support  
---
## Future Improvements
- Add support for environment variables  
- Implement tab auto-completion  
- Add advanced error handling  
- Improve history persistence (save across sessions)
---
## Author  
- Mahir Faisal  
- [GitHub Profile](https://github.com/MahirFaisal08)
---
## License

This project is licensed under the **MIT License** – you are free to use, modify, and distribute this software with proper credit.  
For more details, see the [LICENSE](LICENSE) file in this repository or visit the official [MIT License](https://opensource.org/licenses/MIT).

---
## Contributing  
Contributions, issues, and feature requests are welcome!  

If you’d like to contribute:  
1. **Fork** the repository  
2. Create a new branch (`git checkout -b feature-branch`)  
3. Make your changes and commit (`git commit -m "Add new feature"`)  
4. **Push** to your branch (`git push origin feature-branch`)  
5. Open a **Pull Request**  

 Check the [Issues](../../issues) page for open tasks or feature requests.  
