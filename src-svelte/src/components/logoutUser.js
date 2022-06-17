import { auth_state } from "../stores/auth_state";

let auth_subbed_data;
auth_state.subscribe((value) => {
    auth_subbed_data = value;
});

export default function logoutUser() {
    auth_state.update((curData) => {
        curData.loggedIn = false;
        curData.token = "";
        localStorage.setItem("loggedIn", false);
        localStorage.setItem("token", "");
        return curData;
    });
}