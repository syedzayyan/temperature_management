import { writable } from 'svelte/store';
export const auth_state = writable({loggedIn : Boolean(localStorage.getItem("loggedIn")) || false,
                     token : localStorage.getItem("token") || null, 
                     admin : localStorage.getItem("admin") || false,
                     email : localStorage.getItem("email") || ""});