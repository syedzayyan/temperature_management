<script>
    import { Button } from "carbon-components-svelte";
    import Logout from "carbon-icons-svelte/lib/Logout.svelte";
    import Login from "carbon-icons-svelte/lib/Login.svelte";
    import { auth_state } from "../stores/auth_state";
    import logoutUser from "./logoutUser";

    let auth_subbed_data;
    auth_state.subscribe((value) => {
        auth_subbed_data = value;
    });

</script>

<div>
    {#if auth_subbed_data.loggedIn}
    <Button
        on:click={logoutUser}
        kind="tertiary"
        iconDescription="Login"
        icon={Logout}>Logout</Button
    >
    {:else}
    <Button
    href = "/"
    kind="tertiary"
    iconDescription="Logout"
    icon={Login}>Login</Button
>
    {/if}
</div>
