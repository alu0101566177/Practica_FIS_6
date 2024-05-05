const reserveBook = async (id) => {
  const requestOptions = {
    method: "POST",
    redirect: "follow"
  };

  const res = await fetch(`/reserve/${id}`, requestOptions);
  if (res.ok)
    alert("Reservado correctamente");
  else if (res.status == 400)
    alert("Ya existe una reserva en curso de este libro");
  else
    alert("Debe iniciar sesión para reservar libros");
};

