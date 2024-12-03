import matplotlib.pyplot as plt

# 读取插入时间数据
data_sizes = []
insert_times = []

with open("insert_times.txt", "r") as file:
    for line in file:
        size, time = map(float, line.split())
        data_sizes.append(size)
        insert_times.append(time)

# 读取查找时间数据
search_times = []

with open("search_times.txt", "r") as file:
    for line in file:
        size, time = map(float, line.split())
        search_times.append(time)

# 绘制插入时间曲线图
plt.figure(figsize=(10, 6))
plt.plot(data_sizes, insert_times, label="Insert Time", color="blue")
plt.xlabel("Number of Students")
plt.ylabel("Time (seconds)")
plt.title("Cuckoo Hash Table Insert Time Complexity")
plt.legend()
plt.grid(True)
plt.show()

# 绘制查找时间曲线图
plt.figure(figsize=(10, 6))
plt.plot(data_sizes, search_times, label="Search Time", color="red")
plt.xlabel("Number of Students")
plt.ylabel("Time (seconds)")
plt.title("Cuckoo Hash Table Search Time Complexity")
plt.legend()
plt.grid(True)
plt.show()