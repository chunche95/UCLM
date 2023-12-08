package Controller;

import Domain.Individuo;
import dao.IndividuoDao;
import lombok.extern.slf4j.Slf4j;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.GetMapping;


@Controller
@Slf4j // Para poder usar log.info
public class ControladorREST {

    @Autowired // Inyecta el repositorio para poder acceder a la base de datos
    private IndividuoDao individuoDao; // El repositorio es una interfaz que extiende de CrudRepository

    @GetMapping("/")
    public String comienzo(Model model) {
        //Iterable<Individuo> individuos = individuoDao.findAll();
        String individuos = individuoDao.findAll().toString();
        log.info("Ejecutando el controlador MVC");
        model.addAttribute("individuos", individuos);
        return "indice";
    }

}
