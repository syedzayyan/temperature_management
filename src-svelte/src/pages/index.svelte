<script>
    import { metatags } from "@roxi/routify";
    import ArduinoList from "../components/ArduinoList.svelte";
    metatags.title = "Dashboard";
    import Login from "../components/Login.svelte"
    import { auth_state } from '../stores/auth_state';

    let auth_subbed_data;
    auth_state.subscribe(value => {
		auth_subbed_data = value;
	});
</script>

{#if auth_subbed_data.loggedIn}
    <ArduinoList />
{:else}
    <Login />
{/if}