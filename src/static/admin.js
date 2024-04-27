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
      <label>Id:</label>
      <input type="text" class="form-control" disabled value="${id}" />
    </div>
    <div class="form-group mx-2">
      <label>Título:</label>
      <input type="text" class="form-control" disabled value="${title}" />
    </div>
    <div class="form-group mx-2">
      <label>Autor:</label>
      <input type="text" class="form-control" disabled value="${author}" />
    </div>
    <div class="form-group mx-2">
      <label>Descripción:</label>
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
const User = ({ id, name, email, password }) => {
  return `
  <li class="card">
    <div class="form-group mx-2">
      <label>Id:</label>
      <input type="text" class="form-control" disabled value="${id}" />
    </div>
    <div class="form-group mx-2">
      <label >Nombre:</label>
      <input type="text" class="form-control" disabled value="${name}" />
    </div>
    <div class="form-group mx-2">
      <label>Email:</label>
      <input type="text" class="form-control" disabled value="${email}" />
    </div>
    <div class="form-group mx-2">
      <label>Contraseña:</label>
      <textarea class="form-control" rows="3" disabled>${password}</textarea>
    </div>
    <button class="btn btn-danger m-2" onclick="userDeleteEv(${id})">Borrar usuario</button>
  </li>
  `;
};

// Validators
const emptyAttributes = (book) => {
  return Object.keys(book).some((key) => book[key] === "");
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

// APIs
const bookAPI = new ModelAPI("book", window.auth_token);
const userAPI = new ModelAPI("user", window.auth_token);

// Events
const paintBooks = (books) => {
  bookAPI.getModel().then((bookList) => {
    books.innerHTML = "";
    bookList.forEach((book) => (books.innerHTML += Book(book)));
  });
};
const paintUsers = (users) => {
  userAPI.getModel().then((userList) => {
    users.innerHTML = "";
    userList.forEach((user) => (users.innerHTML += User(user)));
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
  bookAPI.postModel(json);
  paintBooks(books);
};
const userSubmit = (ev, form) => {
  ev.preventDefault();
  const body = new FormData(form);
  const json = Object.fromEntries(body);
  if (emptyAttributes(json)) {
    alert("Faltan atributos en el formulario del usuario");
    return;
  }
  userAPI.postModel(json);
  paintUsers(users);
};
const bookDeleteEv = (id) => {
  if (!confirm("Estas seguro?")) return;
  bookAPI.deleteModel(id);
  paintBooks(books);
};
const userDeleteEv = (id) => {
  if (!confirm("Estas seguro?")) return;
  userAPI.deleteModel(id);
  paintUsers(users);
};

const books = document.querySelector("#book-list");
const users = document.querySelector("#user-list");

const bookForm = document.querySelector("#book-form");
const userForm = document.querySelector("#user-form");

const logoutBtn = document.querySelector("#logout");

bookForm.addEventListener("submit", (ev) => bookSubmit(ev, bookForm));
userForm.addEventListener("submit", (ev) => userSubmit(ev, userForm));
logoutBtn.addEventListener("click", logout);

paintBooks(books);
paintUsers(users);
