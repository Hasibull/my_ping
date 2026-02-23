# My ping

Mimicking Windows/Linux `ping` utility. Which support Linux/macOS and Windows.

## ✅ Features

- ICMP Echo Request/Reply support
- Measures Round-Trip Time (RTT)
- Cross-platform using conditional compilation
- Uses raw sockets on Unix-like systems and IP Helper API on Windows

## 🛠️ Build Instructions

### Linux/macOS

```bash
mkdir build && cd build
cmake ..
make
./my_ping 8.8.8.8
```

### Windows

```python
mkdir build
cd build
cmake ..
cmake --build . --config Release

.\my_ping 8.8.8.8
```