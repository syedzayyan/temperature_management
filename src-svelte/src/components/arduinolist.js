import { auth_state } from "../stores/auth_state";
import logoutUser from "./logoutUser";
import { url } from "./url"

let auth_subbed_data;

auth_state.subscribe((value) => {
    auth_subbed_data = value;
});

export const arduinolist = async () => {
    let arduino_data = [];
    const requestOptions = {
        method: "GET",
        headers: {
            "Content-Type": "application/json",
            Authorization: `Bearer ${auth_subbed_data.token}`,
        },
    };

    const response = await fetch(
        `${url}/arduino`,
        requestOptions
    );
    const data = await response.json();

    if (!response.ok) {
        if(response.status == 401){
            logoutUser();
            return
        }
        alert("Problem With fetching Arduino Data");
    } else {
        arduino_data = data;
    }
    return arduino_data
}

export const freezerList = async (ard_id) => {
    let freezer_data = [];
    const requestOptions = {
        method: "GET",
        headers: {
            "Content-Type": "application/json",
            Authorization: `Bearer ${auth_subbed_data.token}`,
        },
    };

    const response = await fetch(
        `${url}/freezer/${ard_id}`,
        requestOptions
    );
    const data = await response.json();

    if (!response.ok) {
        alert("Problem With fetching Freezer Data");
    } else {
        freezer_data = data;
    }
    return freezer_data
}