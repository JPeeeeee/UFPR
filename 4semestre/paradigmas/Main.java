import java.util.*;
import monopoly.Controllers.PlanetasDB;

public class Main {
     
    public static void main(String[] args) {

        PlanetasDB listaPlanetas = new PlanetasDB();
        Vector<Jogador> jogadores = new Vector<Jogador>();
        Vector<Planeta> planetas = new Vector<Planeta>();

        for (Integer i = 0; i < 6; i++) {
            Jogador jogador = new Jogador();

            jogadores.add(jogador);
        }
    }
}
