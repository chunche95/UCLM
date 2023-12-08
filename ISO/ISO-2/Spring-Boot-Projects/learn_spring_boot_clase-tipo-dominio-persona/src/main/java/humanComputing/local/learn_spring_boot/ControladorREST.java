package humanComputing.local.learn_spring_boot;

import Domain.Individuo;
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
        model.addAttribute("variable", variablehola);
        log.info("Ejecutando el controlador MVC");

        Individuo persona1 = new Individuo();
        persona1.setNombre("Juan");
        persona1.setApellido("Perez");
        persona1.setEdad(25);
        persona1.setEmail("jperez@email.local");
        persona1.setTelefono("555-555-5555");


        model.addAttribute("variable_privada", varprivada);

        model.addAttribute("personaRegistrada", persona1);
        return "indice";
    }

}
