// Components
const Book = ({
  id,
  title,
  author,
  description,
  image_url,
  library_id,
  stock,
}) => {
  return `
  <li class="card">
    <div class="form-group mx-2">
      <label >Id:</label>
      <input type="text" class="form-control" disabled value="${id}" />
    </div>
    <div class="form-group mx-2">
      <label >Título:</label>
      <input type="text" class="form-control" disabled value="${title}" />
    </div>
    <div class="form-group mx-2">
      <label>Autor:</label>
      <input type="text" class="form-control" disabled value="${author}" />
    </div>
    <div class="form-group mx-2">
      <label ption">Descripción:</label>
      <textarea class="form-control" rows="3" disabled>${description}</textarea>
    </div>
    <div class="form-group mx-2">
      <label>URL de la imagen:</label>
      <input type="text" class="form-control" disabled value="${image_url}" />
    </div>
    <div class="form-group mx-2">
      <label>ID de biblioteca:</label>
      <input type="number" class="form-control" disabled value="${library_id}" />
    </div>
    <div class="form-group mx-2 mb-2">
      <label>Stock:</label>
      <input type="number" class="form-control" disabled value="${stock}" />
    </div>
    <button class="btn btn-danger m-2" onclick="bookDeleteEv(${id})">Borrar libro</button>
  </li>
  `;
};
// Validators
const emptyAttributes = (book) => {
  return Object.keys(book).some((key) => book[key] === "");
};

// Requests
const bookPost = async (book) => {
  const myHeaders = new Headers();
  if (window.auth_token) myHeaders.append("Authorization", window.auth_token);
  myHeaders.append("Content-Type", "application/json");
  const raw = JSON.stringify(book);
  const requestOptions = {
    method: "POST",
    headers: myHeaders,
    body: raw,
    redirect: "follow",
  };

  try {
    const response = await fetch("/api/book", requestOptions);
    await response.json();
  } catch (error) {
    alert("Failed book creation");
  }
};
const bookGet = async () => {
  const requestOptions = {
    method: "GET",
    redirect: "follow",
  };
  try {
    const response = await fetch("/api/books", requestOptions);
    return await response.json();
  } catch (error) {
    console.log(error);
    alert("No se pudo obtener los libros");
    return [];
  }
};
const bookDelete = async (id) => {
  console.log("Delete", id);
  const myHeaders = new Headers();
  myHeaders.append("Authorization", window.auth_token);

  const requestOptions = {
    method: "DELETE",
    headers: myHeaders,
    redirect: "follow",
  };

  const response = await fetch(`/api/book/${id}`, requestOptions);
  if (response.ok) return;
  alert("No se pudo eliminar el libro");
};

// Events
const paintBooks = (books) => {
  bookGet().then((bookList) => {
    books.innerHTML = "";
    bookList.forEach((book) => (books.innerHTML += Book(book)));
  });
};
const bookSubmit = (ev, form) => {
  ev.preventDefault();
  const body = new FormData(form);
  const json = Object.fromEntries(body);
  json.stock = parseInt(json.stock) || -1;
  json.library_id = parseInt(json.library_id) || null;
  if (emptyAttributes(json)) {
    alert("Faltan atributos en el formulario del libro");
    return;
  }
  bookPost(json);
  paintBooks(books);
};
const bookDeleteEv = (id) => {
  if (!confirm("Estas seguro?")) return;
  bookDelete(id);
  paintBooks(books);
};
const logout = async () => {
  if (!confirm("Estas seguro?")) return;
  const requestOptions = {
    method: "DELETE",
    redirect: "follow",
  };
  await fetch(`/login`, requestOptions);
  window.location.replace("/admin-login");
};

const books = document.querySelector("#book-list");
const bookForm = document.querySelector("#book-form");
const logoutBtn = document.querySelector("#logout");

bookForm.addEventListener("submit", (ev) => bookSubmit(ev, bookForm));
logoutBtn.addEventListener("click", logout);
paintBooks(books);
