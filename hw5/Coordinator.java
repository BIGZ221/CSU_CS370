import java.time.Instant;
import java.time.Clock;
import java.time.Duration;

class Coordinator {
	public static void main(String[] args) throws InterruptedException {

		int buffSize = Integer.parseInt(args[0]); // Parse all arguments out of args passed in
		int count = Integer.parseInt(args[1]);
		int m = Integer.parseInt(args[2]);
		int n = Integer.parseInt(args[3]);
		int seed = Integer.parseInt(args[4]);


		if (m > 3 || m < 1) {
			System.out.println("Consumers argument was out of range must be between 1 and 3");
			return;
		}


		if (n > 3 || n < 1) {
			System.out.println("Producers argument was out of range must be between 1 and 3");
			return;
		}


		Buffer circBuff = new Buffer(buffSize); // Make the one instance of a buffer
		Producer[] producers = new Producer[n]; // Array of n producers (not yet constructed)
		Consumer[] consumers = new Consumer[m]; // Array of m consumers (not yet constructed)

		int rem = count % n;
		for (int i = 0; i < n; i++) {
			producers[i] = new Producer(circBuff, (count/n)+rem, i+1, seed);
			producers[i].start(); // Construct and start each thread of producers, first producer gets the offset amount if count doesn't divide evenly.
			rem = 0;
		}
		
		rem = count % m;
		for (int i = 0; i < m; i++) {
			consumers[i] = new Consumer(circBuff, (count/m)+rem, i+1);
			consumers[i].start(); // Construct and start each thread of consumers, first consumer get the offset amoutn if count doesn't divide evenly.
			rem = 0;
		}

		try {
			Thread.sleep(1500);
		} catch (Exception e) { }

		int cTotal = 0;
		for (int i = 0; i < m; i++) {
			consumers[i].join();
			cTotal += consumers[i].getChecksum(); // Join all threads back on, while keeping a sum of checksums
		}

		int pTotal = 0;
		for (int i = 0; i < n; i++) {
			producers[i].join();
			pTotal += producers[i].getChecksum(); // Join all threads back on, while keeping a sum of checksums
		}
		
		System.out.printf("\nProducer(s): Finished producing %3d items with checksum being %d%n", count, pTotal);
		System.out.printf("\033[0;4mConsumer(s): Finished consuming %3d items with checksum being %d\033[0;0m%n",count, cTotal);
	}

	//Call this function from your producer or your consumer to get the time stamp to be displayed
	public static String getTime() { // Provided code, didn't edit it
		Clock offsetClock = Clock.offset(Clock.systemUTC(), Duration.ofHours(-9));
		Instant time = Instant.now(offsetClock);
		String timeString = time.toString();
		timeString = timeString.replace('T', ' ');
		timeString = timeString.replace('Z', ' ');
		return(timeString);
	}
}