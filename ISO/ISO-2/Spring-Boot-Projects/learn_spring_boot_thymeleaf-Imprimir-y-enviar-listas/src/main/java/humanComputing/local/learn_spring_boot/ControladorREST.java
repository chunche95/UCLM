package humanComputing.local.learn_spring_boot;

import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;


@Controller
@Slf4j // Para poder usar log.info
public class ControladorREST {
    @Value("${indice.variable_privada}")
    private String varprivada;
    @GetMapping(value = "/")
    public String comienzo(Model model) {

        String variablehola = "Hola, Estamos mandando mensajes desde ControladorREST.java";
        log.info("Ejecutando el controlador MVC");
        model.addAttribute("variable", variablehola);
        model.addAttribute("variable_privada", varprivada);
        return "indice";
    }

}
