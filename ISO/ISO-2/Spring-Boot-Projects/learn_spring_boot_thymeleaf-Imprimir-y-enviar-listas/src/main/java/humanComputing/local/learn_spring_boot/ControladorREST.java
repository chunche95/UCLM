package humanComputing.local.learn_spring_boot;

import lombok.extern.slf4j.Slf4j;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.GetMapping;


@Controller
@Slf4j // Para poder usar log.info
public class ControladorREST {

    @GetMapping("/")
    public String comienzo() {
        log.info("Ejecutando el controlador MVC");
        return "indice";
    }

}
