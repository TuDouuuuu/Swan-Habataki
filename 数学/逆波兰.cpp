/**
样例输入
2
1.000+2/4=
((1+2)*5+1)/4=
样例输出
1.50
4.00
*/
#include <bits/stdc++.h>
using namespace std;
int Judge(char ch){
    //运算符进行优先级划分
    if(ch == '+') return 1;
    if(ch == '-') return 1;
    if(ch == '*') return 2;
    if(ch == '/') return 2;
    if(ch == '(') return 0;
    if(ch == ')') return 0;
}
int main (void){
    string str;
    string s;
    int count ;
    cin>>count;
    while(count--){
        int i=0 ;
        str.clear();
        s.clear() ;
        cin>>str;
        stack<char>mid; //字符串栈 ，用于中缀表达式转后缀表达式
        stack<double>ans;//数字栈 ，用于后缀表达式求值
        while(str[i] != '=')
        {
            if(str[i] == '('){//判断，左括号进栈
                mid.push(str[i]);
                i++;
            }
            else if( str[i] == ')')//遇右括号则将左括号及左括号以上标识符出栈
            {
                while(mid.top()!='(')
                {
                    s = s + mid.top() ;
                    s += ' ';
                    mid.pop() ;
                }
                mid.pop() ;
                i++;
            }
            else if(isdigit(str[i]))//数字或小数点则直接转入后缀表达式
            {
                while(str[i]<='9'&&str[i]>='0' || str[i] =='.')
                {
                    s = s + str[i];
                    i++;
                }
                s += ' ';
            }
            else if(str[i] == '+'||str[i] == '-'||str[i] == '*'||str[i] == '/'){
                while(!mid.empty() && Judge(mid.top()) >= Judge(str[i])){
                //当前运算标识符优先级低于栈顶元素，进行出栈操作
                    s = s + mid.top();
                    s = s + ' ';
                    mid.pop();
                }
                mid.push(str[i]);//将当前运算符进栈
                i++;
 
            }
        }
        while(!mid.empty())//将最后剩余运算符出栈
        {
            s = s + mid.top() ;
            s = s + ' ';
            mid.pop() ;
        }
        string temp;
        stringstream ss(s);
        char a[1000];
        double num;
        while(ss>>temp)
        {
            if( isdigit(temp[0]) ){
                for(i=0;i<temp.length();i++)
                    a[i] = temp[i];
                a[i] ='\0';//最后必须赋 '\0' 否则报错
                num = atof(a);
                //将数字字符串转为数字
                //注意atof()函数不支持string类型，支持char()
                ans.push(num);//将数字进栈
            }
            else{// 运算符操作
                double x,y;
                x = ans.top();
                ans.pop();
                y = ans.top();
                ans.pop();
                //取出栈顶两位元素 ，进行相应操作
                if(temp == "+") num = x + y;
                if(temp == "-") num = y - x;
                if(temp == "*") num = x * y;
                if(temp == "/") num = y / x;
                ans.push(num);//得到元素进栈
            }
        }
        cout<< fixed <<setprecision(2)<<ans.top()<<endl;//输出两位小数；
    }
}
