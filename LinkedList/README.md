## SingleLinkedList 类方法说明

### `find(const T &val)`

#### 功能
在链表中查找值为 `val` 的节点。

#### 参数
- `val`：要查找的值。

#### 返回值
- 如果找到，返回 `true` 并将 `currentPos` 设置为找到的节点。
- 如果未找到，返回 `false`。

#### 操作后变化
- 如果找到，`currentPos` 将指向找到的节点。
- 如果未找到，`currentPos` 不变。

### `insert(const T &val)`

#### 功能
在链表中插入一个值为 `val` 的新节点。

#### 参数
- `val`：要插入的值。

#### 操作后变化
- 如果链表为空，`head` 和 `currentPos` 都将指向新插入的节点。
- 否则，新节点将插入到 `currentPos` 之后，`currentPos` 更新为新节点。
- 链表的大小 `size` 增加 1。

### `remove()`

#### 功能
删除 `currentPos` 所指向的节点。

#### 操作后变化
- 如果 `currentPos` 为空，不进行任何操作。
- 如果 `currentPos` 是头节点，`head` 更新为 `head->next`，并删除原头节点，`currentPos` 更新为新的头节点。
  - **链表只有一个元素**：正确清空链表。
  - **链表有多个元素**：如果 `find` 方法找到头节点并将 `currentPos` 设置为头节点，`remove` 方法正确删除头节点而不会将链表设为空，并将 `currentPos` 指向下一个节点。在 `find` 头元素时会发生这种情况。
- 否则，遍历链表找到 `currentPos` 的前一个节点，将其 `next` 指针更新为 `currentPos->next`，删除 `currentPos`，并将 `currentPos` 更新为前一个节点。
- 链表的大小 `size` 减少 1。

#### 好处
- **连续删除操作**：如果需要连续删除多个节点，指向前一个节点可以方便地继续删除操作，而不需要重新查找前一个节点。
- **避免悬挂指针**：删除当前节点后，`currentPos` 指向前一个节点，可以避免 `currentPos` 成为悬挂指针（指向已删除的节点）。
- **防止空指针操作**：如果删除后指向后一个节点，删除最后一个元素后 `currentPos` 会指向 `nullptr`，可能导致意外的 `get` 操作引发程序终止。

> 在这个`remove()`函数下，示例代码的最后一行输出将是`1.5 2 4.7 8.8`而不是参考示例的`1.5 2 9 8.8`