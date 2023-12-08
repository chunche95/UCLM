package humanComputing.local.learn_spring_boot;

import lombok.extern.slf4j.Slf4j;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;

@RestController
@Slf4j // Para poder usar log.info
public class ControladorREST {

    @GetMapping("/")
    public String comienzo() {
        log.info("Ejecutando el controlador REST");
        log.debug("Modo debug - +info");
        return "Hola Mundo en Spring";
    }

}
