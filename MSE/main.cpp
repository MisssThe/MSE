#include "Include/Canvas.h"
//#include "Include/General/Container/Map.h"
//#include "CustomVal.h"

//Start函数执行完后可以完全卸载掉内存
void Start()
{
    Canvas canvas;
    canvas.Invoke();
}

int main() {
    Start();
    return 0;
}
