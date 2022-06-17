<script>
    import { FluidForm, TextInput, PasswordInput, Button } from "carbon-components-svelte";
    import { auth_state } from '../stores/auth_state';
    import { url } from "./url"


    let email;
    let password;  

    const submitLogin = async () => {
        const requestOptions = {
            method: "POST",
            headers: { "Content-Type": "application/x-www-form-urlencoded" },
            body: JSON.stringify(
                `grant_type=&username=${email}&password=${password}&scope=&client_id=&client_secret=`
            ),
        };

        const response = await fetch(
            `${url}/api/token`,
            requestOptions
        );
        const data = await response.json();
        if (!response.ok) {
            loginMessage = "Everything Broken"
        } else {
            auth_state.update((curData) => {
                curData.loggedIn = true;
                curData.token = data.access_token;
                curData.admin = data.admin
                curData.email = data.email
                localStorage.setItem("loggedIn", true)
                localStorage.setItem("token", data.access_token)
                localStorage.setItem("email", data.email)
                localStorage.setItem("admin", data.admin)
                return curData
            })
        }
    };
</script>

<div>
    <FluidForm>
        <TextInput
            bind:value={email}
            labelText="User name"
            placeholder="Enter user name..."
            required
        />
        <PasswordInput
            bind:value={password}
            required
            type="password"
            labelText="Password"
            placeholder="Enter password..."
        />
        <Button on:click={submitLogin}>Submit</Button>
    </FluidForm>
</div>
