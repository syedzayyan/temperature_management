<script>
    import { Select, SelectItem, Button } from "carbon-components-svelte";
    import { onMount } from "svelte";
    import { auth_state } from "../stores/auth_state";
    import TrashCan from "carbon-icons-svelte/lib/TrashCan.svelte";
    import { url } from "./url"

    
    let selected = 0;
    let user_data = [];
    let auth_subbed_data;

    auth_state.subscribe((value) => {
        auth_subbed_data = value;
    });
    const requestOptions = {
        method: "GET",
        headers: {
            "Content-Type": "application/json",
            Authorization: `Bearer ${auth_subbed_data.token}`,
        },
    };
    onMount(async () => {           
        fetch(`${url}/api/users`, requestOptions)
                .then((res) => res.json())
                .then((data) => {
                   user_data = data
                });
    });
    async function submitForm() {
        const requestOptions = {
            method: "DELETE",
            headers: { 
                "Content-Type": "application/json",
                Authorization: `Bearer ${auth_subbed_data.token}`,
            },
        };

        const response = await fetch(
            `${url}/api/users/${selected}`,
            requestOptions
        );

        if (!response.ok) {
            alert("Problem");
        }
        window.location.reload();
    }
</script>

<div>
    <Select bind:selected labelText="Select User to delete">
        <SelectItem value={0} text="Select User" disabled hidden />
        {#each user_data as item}
            <SelectItem value={item.id} text={item.email} />
        {/each}
    </Select>
    <Button kind="danger-tertiary" iconDescription="Delete" icon={TrashCan} on:click={submitForm}>Delete User</Button>
</div>
