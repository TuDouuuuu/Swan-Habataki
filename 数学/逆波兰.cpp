/**
��������
2
1.000+2/4=
((1+2)*5+1)/4=
�������
1.50
4.00
*/
#include <bits/stdc++.h>
using namespace std;
int Judge(char ch){
    //������������ȼ�����
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
        stack<char>mid; //�ַ���ջ ��������׺���ʽת��׺���ʽ
        stack<double>ans;//����ջ �����ں�׺���ʽ��ֵ
        while(str[i] != '=')
        {
            if(str[i] == '('){//�жϣ������Ž�ջ
                mid.push(str[i]);
                i++;
            }
            else if( str[i] == ')')//���������������ż����������ϱ�ʶ����ջ
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
            else if(isdigit(str[i]))//���ֻ�С������ֱ��ת���׺���ʽ
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
                //��ǰ�����ʶ�����ȼ�����ջ��Ԫ�أ����г�ջ����
                    s = s + mid.top();
                    s = s + ' ';
                    mid.pop();
                }
                mid.push(str[i]);//����ǰ�������ջ
                i++;
 
            }
        }
        while(!mid.empty())//�����ʣ���������ջ
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
                a[i] ='\0';//�����븳 '\0' ���򱨴�
                num = atof(a);
                //�������ַ���תΪ����
                //ע��atof()������֧��string���ͣ�֧��char()
                ans.push(num);//�����ֽ�ջ
            }
            else{// ���������
                double x,y;
                x = ans.top();
                ans.pop();
                y = ans.top();
                ans.pop();
                //ȡ��ջ����λԪ�� ��������Ӧ����
                if(temp == "+") num = x + y;
                if(temp == "-") num = y - x;
                if(temp == "*") num = x * y;
                if(temp == "/") num = y / x;
                ans.push(num);//�õ�Ԫ�ؽ�ջ
            }
        }
        cout<< fixed <<setprecision(2)<<ans.top()<<endl;//�����λС����
    }
}
