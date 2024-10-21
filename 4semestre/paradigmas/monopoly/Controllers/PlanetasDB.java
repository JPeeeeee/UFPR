package monopoly.Controllers;

import java.util.Arrays;

// 1. Tatooine
// 2. Jakku
// 3. Dantooine
// 4. Kamino
// 5. Mon Cala
// 6. Naboo
// 7. Hoth
// 8. Mustafar
// 9. Felucia
// 10. Endor
// 11. Kashyyyk
// 12. Zeffo
// 13. Coruscant
// 14. Bespin
// 15. Taris
// 16. Geonosis
// 17. Ryloth
// 18. Lothal
// 19. Scarif
// 20. Canto Bight
// 21. Alderaan
// 22. Corellia
// 23. Dagobah

enum PlanetasEnum {
    Tatooine, Jakku, Dantooine, Kamino, MonCala, Naboo, Hoth, Mustafar, Felucia, Endor, Kashyyyk, Zeffo, Coruscant, Bespin, Taris, Geonosis, Ryloth, Lothal, Scarif, CantoBight, Alderaan, Corellia, Dagobah
}

public class PlanetasDB {
    private PlanetasDB[] planetas;

    public void PlanetsDB() {
        Arrays.asList(PlanetasEnum.values()).forEach(planeta -> System.err.println(planeta));
    }
}
