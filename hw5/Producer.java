import java.lang.Exception;
import java.util.Random;

public class Producer extends java.lang.Thread {
	//Necessary variables and object declaration
	Random randomWithSeed;
	Buffer circBuff;
	int count;
	int id;
	private boolean producing = false;
	private int produced;
	private int checkSum = 0;

	public Producer(Buffer buff, int count, int id, int seed) { // Constructor
		this.randomWithSeed = new Random(seed);
		this.circBuff = buff;
		this.count = count;
		this.produced = 0;
		this.checkSum = 0;
		this.id = id;
	}

	public synchronized int getChecksum() { // Checksum getter
		return this.checkSum;
	}

	private void random_sleep(int max) // Sleep for some random time
    throws InterruptedException {
        long milliseconds = (long)(max*Math.random());
        Thread.sleep(milliseconds);
    }

	private synchronized void produce(int num) throws InterruptedException {
		try {
			while (this.circBuff.isFull() || producing) { // While the buffer is full or a thread is already producing, wait for 500ms then try again or till you get notified
				this.wait(500);
			}
			producing=true;
			this.circBuff.push(num);
			System.out.printf("Producer %3d inserted %3d  at  index %2d at time %s%n", this.id, num, this.circBuff.getFront(), Coordinator.getTime());
			System.out.flush();
			this.checkSum += num; // Increment my checksum
			this.produced += 1; // Increment how many I've produced
			
		} catch (Exception e) { }
		producing = false;
		this.notify();
	}

	@Override
	public void run() {
		try {
			//random_sleep(50);
		} catch (Exception e) {}
		while (this.produced < this.count) {
			try {
				int tmp = this.randomWithSeed.nextInt(100); // Get random val
				random_sleep(100); // Sleep for 100 to give somed random variety
				produce(tmp);
			} catch (Exception e) { }
		}
	}
}
