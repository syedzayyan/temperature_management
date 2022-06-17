<script>
    import {
        FluidForm,
        TextInput,
        PasswordInput,
        Button,
    } from "carbon-components-svelte";
    import { auth_state } from "../stores/auth_state";
    import { url } from "./url"

    let password;
    let email;
    let auth_subbed_data;
    let created = "";

    auth_state.subscribe((value) => {
        auth_subbed_data = value;
    });

    const submitForm = async () => {
        const requestOptions = {
            method: "POST",
            headers: { 
                "Content-Type": "application/json",
                Authorization: `Bearer ${auth_subbed_data.token}`,
            },
            body: JSON.stringify({
                'arduinoname': email,
                'password_hash': password,
            })
        };

        const response = await fetch(
            `${url}/arduino`,
            requestOptions
        );

        if (!response.ok) {
            alert("Problem");
        } else {
            window.location.reload();
        }
    };
</script>

<div>
    <h1>New Arduino {created}</h1>
    <p>Please remember the password!</p>
    <FluidForm>
        <TextInput labelText="Name" placeholder="Enter an Arduino Name" required bind:value={email}/>
        <PasswordInput
            bind:value={password}
            required
            type="password"
            labelText="Password"
            placeholder="Enter password..."
        />
        <Button on:click = {submitForm}>Submit</Button>
    </FluidForm>
</div>
