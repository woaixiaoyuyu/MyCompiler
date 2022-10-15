#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * 主要由四个函数构成
 * 1）next()：获取下一个token，忽略空白符
 * 2）program()：语法分析入口
 * 3）expression(level)：解析表达式
 * 4）eval()：虚拟机入口，用于解释目标代码
 * */

int token;            // current token
char *src, *old_src;  // pointer to source code string;
size_t poolsize;         // default size of text/data/stack
int line;             // line number

void next() {
    token = *src++;
}

void expression(int level) {
    // do nothing
}

void program() {
    next();                  // get next token
    while (token > 0) {
        printf("token is: %c\n", token);
        next();
    }
}

int eval() { // do nothing yet
    return 0;
}

int main(int argc, char **argv)
{
    size_t i;
    FILE *fd;

    argc--;
    argv++;

    poolsize = 256 * 1024; // arbitrary size
    line = 1;

    if ((fd = fopen(*argv, "r")) < 0) {
        printf("could not open(%s)\n", *argv);
        return -1;
    }

    if (!(src = old_src = malloc(poolsize))) {
        printf("could not malloc(%zu) for source area\n", poolsize);
        return -1;
    }

    // read the source file
    if ((i = fread(src, sizeof(char), poolsize - 1, fd)) <= 0) {
        printf("read() returned %zu\n", i);
        return -1;
    }
    src[i] = 0; // add EOF character
    printf("%s\n", src);
    fclose(fd);

    program();
    return eval();
}
