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
    @Value("${indice.variable_privada}")
    private String varprivada;
    @GetMapping(value = "/")
    public String comienzo(Model model) {

        String variablehola = "Hola, Estamos mandando mensajes desde ControladorREST.java";
        model.addAttribute("variable", variablehola);
        log.info("Ejecutando el controlador MVC");
        // Crear un objeto de tipo Individuo y mandarlo a la vista indice.html
        Individuo persona1 = new Individuo();
        persona1.setNombre("Ciao");
        persona1.setApellido("Di Girolamo");
        persona1.setEdad(25);
        persona1.setEmail("cdg@email.local");
        persona1.setTelefono("555-555-5555");
        persona1.setPassword("12345678");
        // Crear un segundo objeto de tipo Individuo y mandarlo a la vista indice.html
        Individuo persona2 = new Individuo();
        persona2.setNombre("Christian");
        persona2.setApellido("Jobs");
        persona2.setEdad(36);
        persona2.setEmail("christian.jobs@local");
        persona2.setTelefono("555-555-5555");
        persona2.setPassword("12345678");


        /**

        List<Individuo> listaPersonas = new ArrayList<>();

        listaPersonas.add(persona1);
        listaPersonas.add(persona2);
        */

        // Lista vacia
        // List lpersonas = Arrays.asList();

        // Lista con dos objetos de tipo Individuo
        List lpersonas = Arrays.asList(persona1, persona2);

        model.addAttribute("lpersonas", lpersonas);

        return "indice";
    }

}
