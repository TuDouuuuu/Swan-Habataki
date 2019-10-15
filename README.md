# zjut14template
浙江工业大学ACM集训队2019/8-2019/11 zjut14 ACM-ICPC模板。
因为腾讯文档一卡一卡的+导出来并没有代码块，感到了被欺骗，被蔡学长安利了LaTex，感觉kuangbin的板子真好看。

感谢：https://github.com/Chen-Jr/ICPC-Code-Template-in-Latex

##编辑说明
1. 每次在一级目录中增加完新的一级后需要修改`config`。
2. 主文件中的 `head`、`tail`、`main.cpp`文件**最好不要**修改。
3. 一级目录中的`config`文件为当前目录的配置文件，主要用来控制Subsection的输出及判定是否存在Subsubsection。该文件存在四个参数：
<二级目录名称> <代码文件> <tex文件> <三级目录名称>
   - <二级目录名称>：在<>内部填写当前你需要的二级目录（即Subsection）的名称
   - <代码文件>：在<>内部填写在当前二级目录中，你所需要插入的代码(支持`.java`/`.cpp`/`.py`文件)。**如果当前状态下无需代码，则在<>中间留空（如果没有后面两个参数，则可以直接省略<>）**，
   - <tex文件>：在<>内部填写在当前二级目录中，你所需要插入的说明文件`.tex`.**如果当前状态下无需代码，则在<>中间留空（如果没有最后一个参数，则可以直接省略<>）**
   - <三级目录名称>：如果你需要生成一个三级目录，则你只需要在在次项中填写于<二级目录名称>相同的名称。**注意：此时填写的名字代表的是一个二级目录，（是一个文件夹），此时第二个以及第三个参数需要留空**
4. 二级目录同理。
5. 每次上传完代码后都主动修改一下config文件！

##聊天室
**TuDouuuuu：**我写markdown好累。