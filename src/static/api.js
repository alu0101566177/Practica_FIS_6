class ModelAPI {
  constructor(model, token) {
    this._model = model;
    this._token = token;
  }

  async getModel() {
    const myHeaders = new Headers();
    myHeaders.append("Authorization", this._token);

    const requestOptions = {
      method: "GET",
      headers: myHeaders,
      redirect: "follow",
    };

    try {
      const response = await fetch(`/api/${this._model}/`, requestOptions);
      return await response.json();
    } catch (error) {
      console.log(error);
      alert("No se pudo obtener los modelos");
      return [];
    }
  }

  async deleteModel(id) {
    const myHeaders = new Headers();
    myHeaders.append("Authorization", this._token);

    const requestOptions = {
      method: "DELETE",
      headers: myHeaders,
      redirect: "follow",
    };

    const response = await fetch(`/api/${this._model}/${id}`, requestOptions);
    if (response.ok) return;
    alert("No se pudo eliminar el modelo");
  }

  async postModel(model) {
    const myHeaders = new Headers();
    myHeaders.append("Authorization", this._token);
    myHeaders.append("Content-Type", "application/json");

    const raw = JSON.stringify(model);
    const requestOptions = {
      method: "POST",
      headers: myHeaders,
      body: raw,
      redirect: "follow",
    };

    try {
      const response = await fetch(`/api/${this._model}/`, requestOptions);
      await response.json();
    } catch (error) {
      alert("No se ha podido crear el modelo");
    }
  }
}
