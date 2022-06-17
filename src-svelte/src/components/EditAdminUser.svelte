<script>
    import {
        FluidForm,
        TextInput,
        PasswordInput,
        Button,
    } from "carbon-components-svelte";
    import { auth_state } from "../stores/auth_state";
    import { url } from "./url"


    let auth_subbed_data;

    auth_state.subscribe((value) => {
        auth_subbed_data = value;
    });

    let password;
    let email = auth_subbed_data.email;
    let old_password;
    

    const submitForm = async () => {
        const requestOptions = {
            method: "PUT",
            headers: {
                "Content-Type": "application/json",
                Authorization: `Bearer ${auth_subbed_data.token}`,
            },
            body: JSON.stringify({
                email: email,
                old_password: old_password,
                password: password,
            }),
        };

        const response = await fetch(`${url}/api/users/`, requestOptions);

        if (!response.ok) {
            alert("Problem");
        } else {
            window.location.reload();
        }
    };
</script>

<div>
    <h1>Change Admin and Password</h1>
    <p>Please remember the password!</p>
    <FluidForm>
        <TextInput
            labelText="Name"
            placeholder="Enter New Email"
            required
            bind:value={email}
        />
        <PasswordInput
            bind:value={old_password}
            required
            type="password"
            labelText="Old Password"
            placeholder="Enter old password"
        />
        <PasswordInput
            bind:value={password}
            required
            type="password"
            labelText="New Password"
            placeholder="Enter new password"
        />
        <Button on:click={submitForm}>Submit</Button>
    </FluidForm>
</div>
