# bridge
### 目的
将抽象部分与它的实现部分分离，使他们都可以独立地变化

### 适用时机
- 有两个变化纬度及以上且各个维度独立即可使用

### 优缺点
- 抽象与实现分离，扩展能力强，在这些变化维度中任意扩展一个维度，都不需要修改
- 由于聚合关系建立在抽象层，增加系统的理解与设计难度
- 要求变化的纬度独立，有一定局限性
### 注意事项
- 桥接和装饰器都是解决"单一职责"的问题，如果是多纬度且纬度直接独立则用桥接，否则就用装饰器模式
比如：武器的品质和类型是相互独立的，所以使用桥接模式，加密一个数据流和数据流之间是有一定关系的，因此使用装饰器模式
