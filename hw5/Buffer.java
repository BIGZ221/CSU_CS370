
public class Buffer {
    // use syncronized keyword
    int[] buffer;
    int size;
    int front = 0;
    int back = 0;
    int count = 0;

    public Buffer(int buffSize) {
        this.buffer = new int[buffSize];
        this.size = buffSize;
    }

    public synchronized int getFront() {
        return this.front - 1 < 0 ? this.size-1 : this.front - 1;   // Only one thread is allowed to access the front variable at a time
    }

    public synchronized int getBack() {
        return this.back;// Only one thread is allowed to access the back variable at a time
    }

    public synchronized boolean isFull() {
        return this.count >= this.size; // Only one thread is allowed to check if buffer is full at a time
    }

    public synchronized boolean isEmpty() {
        return this.count <= 0; // Only one thread is allowed to check if buffer is empty at a time
    }

    public synchronized void push(int num) throws InterruptedException {
        this.buffer[this.front] = num;  // Pushes num onto the buffer at the front and increments front to the next position, should probably increment front
        this.front += 1;                // first but then on first insert I would be wasting a spot in the array, count keeps track of how many items in array
        this.front %= this.size;
        this.count += 1;
    }

    public synchronized int pop() throws InterruptedException {
        int tmp = this.buffer[this.back];   // Pops the value off the back of the buffer and increments back and decrements count
        this.back += 1;
        this.back %= this.size;
        this.count -= 1;
        return tmp;
    }
}
