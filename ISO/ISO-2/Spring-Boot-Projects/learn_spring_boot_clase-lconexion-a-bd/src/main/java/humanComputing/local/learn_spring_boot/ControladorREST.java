package humanComputing.local.learn_spring_boot;

import Domain.Individuo;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;

import java.util.*;


import static com.fasterxml.jackson.databind.type.LogicalType.Array;


@Controller
@Slf4j // Para poder usar log.info
public class ControladorREST {

    @GetMapping(value = "/")
    public String comienzo(Model model) {
        log.info("Ejecutando el controlador MVC");

        return "indice";
    }

}
