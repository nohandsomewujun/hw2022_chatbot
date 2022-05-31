# hw2022_chatbot
组员：吴骏、胡宇凡、张如凡
工作量1:1:1
本次实验全部数据代码等内容可见Github [hw2022_chatbot](https://github.com/nohandsomewujun/hw2022_chatbot)

## NLP 部分
该部分负责人：吴骏。
这一部分内容教程参考pytorch官方主页中的 [pytorch_tutorial_CHATBOT TUTORIAL](https://pytorch.org/tutorials/beginner/chatbot_tutorial.html)。
（基本是对着教程边学边写的，自己写实在能力不足

### 数据准备与预处理

#### 数据集的选择
为训练我们chatbot的model，我们选用比较容易获取的数据集 [cornell movie-dialogs](https://www.cs.cornell.edu/~cristian/Cornell_Movie-Dialogs_Corpus.html)。这一数据集中包含了*10,292 对电影角色之间的220,579次对话 ， 617部电影中的9,035个电影角色  总共304,713发言量*。这个数据集十分庞大而多样，在语言形式、时间段、情感上等都有很大的变化。我们希望这种多样性使我们的模型能够适应多种形式的输入和查询。不过对于chatbot这一项目，最后训练结果可能会因为训练数据集是电影对话而让chatbot的反馈与日常对话差距较大，不过由于没有其他高质量的数据集，我们还是采取了这一数据集。
#### 数据集的预处理
首先我们从原始数据集创建一个格式良好的文件。其中每一行包含一个由`tab`制表符分隔的查询语句和响应语句对，构成我们数据集中的问答。我们从原始数据集中提取`lineID`, `characterID`, `movieID`, `character`, `text`，对数据进行归类，构成一个字典，将整理后的数据写入formatted_movie_lines.txt中保存。
#### 数据清洗与加载
我们为了加载并使用数据，创建了一个类，存储从单词到索引的映射、索引到单词的反向映射、每个单词的计数和总单词量。并且为了便于处理还增加了添加单词等方法，还添加trim函数来实现清洗不常见单词的功能。
### 定义模型
我们在这里使用了Seq2Seq模型
![](seq2seq_ts.png)
#### 编码器
我们将使用 GRU的双向变体，这意味着基本上有两个独立的RNN：一个以正常的顺序输入输入序列，另一个以相反的顺序输入输入序列。每个网络的输出在 每个时间步骤求和。使用双向GRU将为我们提供编码过去和未来上下文的优势。
![](c653271eb5fb762482bceb5e2464e680.png)
##### 计算图

1.将单词索引转换为词嵌入 embeddings。  
2.为RNN模块打包填充batch序列。  
3.通过GRU进行前向传播。  
4.反填充。  
5.对双向GRU输出求和。  
6.返回输出和最终隐藏状态。  

##### 输入

-   `input_seq`：一批输入句子; _shape =（max_length，batch_size_
-   `input_lengths`：batch中每个句子对应的句子长度列表;_shape=(batch_size)_
-   `hidden`:隐藏状态;_shape =(n_layers x num_directions，batch_size，hidden_size)_

##### 输出

-   `outputs`：GRU最后一个隐藏层的输出特征（双向输出之和）;_shape =（max_length，batch_size，hidden_size）_
-   `hidden`：从GRU更新隐藏状态;_shape =（n_layers x num_directions，batch_size，hidden_size）_

#### 解码器

##### 计算图

1.获取当前输入的词嵌入  
2.通过单向GRU进行前向传播  
3.通过2输出的当前GRU计算注意力权重  
4.将注意力权重乘以编码器输出以获得新的“weighted sum”上下文向量  
5.使用Luong eq.5连接加权上下文向量和GRU输出  
6.使用Luong eq.6预测下一个单词（没有softmax）  
7.返回输出和最终隐藏状态  

##### 输入

-   `input_step`：每一步输入序列batch（一个单词）;_shape =（1，batch_size）_
-   `last_hidden`：GRU的最终隐藏层;_shape =（n_layers x num_directions，batch_size，hidden_size）_
-   `encoder_outputs`：编码器模型的输出;_shape =（max_length，batch_size，hidden_size）_

##### 输出

-   `output`: 一个softmax标准化后的张量， 代表了每个单词在解码序列中是下一个输出单词的概率;_shape =（batch_size，voc.num_words）_
-   `hidden`: GRU的最终隐藏状态;_shape =（n_layers x num_directions，batch_size，hidden_size_

### 训练步骤
由于我们处理的是批量填充序列，因此在计算损失时我们不能简单地考虑张量的所有元素。我们定义`maskNLLLoss`可以根据解码器的输出张量、 描述目标张量填充的`binary mask`张量来计算损失。该损失函数计算与`mask tensor`中的1对应的元素的平均负对数似然。
1.通过编码器前向计算整个批次输入。  
2.将解码器输入初始化为SOS_token，将隐藏状态初始化为编码器的最终隐藏状态。  
3.通过解码器一次一步地前向计算输入一批序列。  
4.如果是 teacher forcing 算法：将下一个解码器输入设置为当前目标;如果是 no teacher forcing 算法：将下一个解码器输入设置为当前解码器输出。  
5.计算并累积损失。  
6.执行反向传播。  
7.裁剪梯度。  
8.更新编码器和解码器模型参数。

### 执行训练
运行repo里的 `train.ipynb` 即可。（模型太大放不到GitHub上，需要请联系本人。

### 使用该部分机器人
我们将repo中的bot封装成一个类，运行repo中`test.py`即可实现*string -> string*的聊天问答。
```python
import bot
a = bot.bot()
while True:
	s = input()
	s = a.speak(s)
	print(s)
```




## 字符串匹配部分




## 接入 QQ 部分

使用 [OneMessage](https://github.com/Hyffer/OneMessage_Server) 项目接入 QQ，收到消息时调用聊天机器人并回复

基于 QQ 协议支持库：[Mirai](https://github.com/mamoe/mirai)


## 总体效果
