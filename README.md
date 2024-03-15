# industrial_PJ
## 24/03/15修改说明
> 开发: 钟明辉 & 黄志涣 <br>
> 日期: 24/03/15
1. 实现相机窗口双击放大和缩小
2. 修改表格边框样式
3. 添加按钮悬停、选中和不可用样式
   
> 新增代码说明
``` cpp
    //窗口状态:正常，最大化，隐藏，未在显示范围内
    enum WINSTATE{_Normal = 0,_Max,_Hide,_Out};
    class camera{
    public:
        //用于给外部调用修改自身窗口状态
        void p_StateChange(WINSTATE state);
    signal:
        //当窗口被双击则发送信号提醒其他窗口此窗口的状态
        void changeState(QString myid,WINSTATE state);
    private slots:
        //此函数与dialog d_changeState 信号绑定，接受其他窗口发出的信号
        void StateChange(QString cid,WINSTATE state);
    }
    class dialog{
    signals:
        //此信号与相机 changeState 信号绑定，当收到信号时，可转发至全部相机窗口，用于解耦信号，提升可读性
        void d_changeState(QString myid,WINSTATE state);
    private:
        //信号绑定和移除函数
        void connect_state(camera*);
        void disconnect_state(camera*);
    }
```
