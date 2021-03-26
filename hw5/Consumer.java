import java.lang.Exception;

class Consumer extends java.lang.Thread {

    Buffer circBuff;
    int id;
	private int count;
	private boolean consuming = false;
	private int checkSum;

    public Consumer(Buffer buff, int count, int id) { //Constructor
        this.circBuff = buff;
        this.count = count;
        this.id = id;
		this.checkSum = 0;
    }

	private void random_sleep(int max) // Provided in example code to sleep for random amount of time
    throws InterruptedException {
        long milliseconds = (long)(max*Math.random());
        Thread.sleep(milliseconds);
    }

	public synchronized int getChecksum() {
		return this.checkSum;	// Get the checksum, only one thread is allowed to do this at a time
	}
	// when buffer is full, consumer hangs
	private synchronized int consume() throws InterruptedException {
		int tmp;
		try {
			random_sleep(100); // Sleep for random 0-99 for some variety, same statement in producer
			while (this.circBuff.isEmpty() || consuming) {	// While the buffer is empty or another thread is consuming, wait for 500ms then check again/ or till you get notified
				this.wait(500);
			}
			consuming = true;
			int back = this.circBuff.getBack();
			tmp = this.circBuff.pop();
			System.out.printf("\033[0;4mConsumer %3d consumed %3d from index %2d at time\033[0;0m %s%n", this.id, tmp, back, Coordinator.getTime());
			System.out.flush();
			this.count -= 1;
		} catch (Exception e) { tmp = 0; }
		consuming = false;
		this.notifyAll(); // Notify all consumer threads that they can consume, only one will actually get to though
		return tmp;
	}

    @Override
	public void run() {
		try {
		random_sleep(50); // Sleep a little to give a producer time to produce something, only ran once
		} catch (Exception e) { }

		while (this.count > 0) {
			try {
				this.checkSum += consume(); // Increment checksum and repeat till you counted all the items you were expected to
			} catch (Exception e) { }
		}
		
	}

}