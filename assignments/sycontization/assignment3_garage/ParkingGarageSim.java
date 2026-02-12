import java.util.Random;
import java.util.concurrent.Semaphore;

public class ParkingGarageSim {

    static class ParkingGarage {
        private final int capacity;
        private final Semaphore spots;
        private int used = 0;

        public ParkingGarage(int capacity) {
            this.capacity = capacity;
            this.spots = new Semaphore(capacity, true);
        }

        public void park(String carName) {
            try {
                System.out.println(carName + " is trying to park...");

                spots.acquire();

                synchronized (this) {
                    used++;
                    System.out.println(carName + " has entered. Slots used: " + used);
                }

                int ms = 1000 + new Random().nextInt(2001);
                Thread.sleep(ms);

                synchronized (this) {
                    used--;
                    System.out.println(carName + " left. Slots freed.");
                }

                spots.release();

            } catch (InterruptedException e) {
                System.out.println(carName + " got interrupted.");
            }
        }
    }

    public static void main(String[] args) throws InterruptedException {
        ParkingGarage garage = new ParkingGarage(3);

        Thread[] cars = new Thread[10];

        for (int i = 0; i < 10; i++) {
            String name = "Car-" + (i + 1);
            cars[i] = new Thread(() -> garage.park(name));
        }

        for (Thread t : cars) t.start();
        for (Thread t : cars) t.join();

        System.out.println("Done.");
    }
}
