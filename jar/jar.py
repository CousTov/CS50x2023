class Jar:
    def __init__(self, capacity=12):
        if capacity < 0:
            raise ValueError
        self._capacity = capacity
        self._size = 3

    def __str__(self):
        return self.size * "cookie"

    def deposit(self, n):
        if n > capacity:
            raise ValueError
        if self.size + n > self.capacity:
            raise ValueError
        self.size += n

    def withdraw(self, n):
        if self.size < n:
            raise ValueError
        self.size -= n

    @property
    def capacity(self):
        return self._capacity

    @property
    def size(self):
        return self._size

