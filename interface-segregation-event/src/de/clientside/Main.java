package de.clientside;

import de.tiere.PigTooFatListener;
import de.tiere.Schwein;

public class Main {

    private Metzger metzger = new Metzger();
    private Spediteuer spediteuer = new Spediteuer();
	public static void main(String[] args) {

		new Main().run();
	}

	private void run() {
		Schwein schwein = new Schwein("Miss Piggy");

        schwein.addPigTooFatListener(new SchweineMetzgerAdapter());
        schwein.addPigTooFatListener(s-> spediteuer.fahren(s));
        schwein.addPigTooFatListener(spediteuer::fahren);

		for (int i = 0; i < 11; i++) {
			schwein.fuettern();
		}
    }

    class SchweineMetzgerAdapter implements PigTooFatListener {

        @Override
        public void pigTooFat(final Schwein dickesSchwein) {
            metzger.schlachten(dickesSchwein);
        }
    }

}

class Metzger {


    public void schlachten(final Object tier) {
        System.out.println("Messer wetz!");
    }
}

class Spediteuer {


    public void fahren(final Object ware) {
        System.out.println("wir fahren auf der autobahn ");
    }
}





