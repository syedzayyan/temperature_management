<script>
    import { Select, SelectItem, Button } from "carbon-components-svelte";
    import { auth_state } from "../stores/auth_state";
    import { freezerList } from "./arduinolist";
    import TrashCan from "carbon-icons-svelte/lib/TrashCan.svelte";
    import { url } from "./url"

    export let arduinoID;
    let auth_subbed_data;

    auth_state.subscribe((value) => {
        auth_subbed_data = value;
    });
    let freezer_data = [];
    let selected = 0;

    $: freezerList(arduinoID).then((res) => (freezer_data = res));

    async function submitForm() {
        const requestOptions = {
            method: "DELETE",
            headers: {
                "Content-Type": "application/json",
                Authorization: `Bearer ${auth_subbed_data.token}`,
            },
        };

        const response = await fetch(
            `http://127.0.0.1:8000/freezer/${selected}`,
            requestOptions
        );

        if (!response.ok) {
            alert("Problem");
        }
        window.location.reload();
    }
    async function deleteTempData() {
        const requestOptions = {
            method: "DELETE",
            headers: {
                "Content-Type": "application/json",
                Authorization: `Bearer ${auth_subbed_data.token}`,
            },
        };

        const response = await fetch(
            `${url}/temperature/${selected}`,
            requestOptions
        );

        if (!response.ok) {
            alert("Problem");
        }
        window.location.reload();
    }
</script>

<div>
    <Select bind:selected>
        <SelectItem value={0} text="Select Freezer" disabled hidden />
        {#each freezer_data as item}
            <SelectItem value={item.id} text={item.name} />
        {/each}
    </Select>

    <Button kind="danger-tertiary" iconDescription="Delete" icon={TrashCan} on:click={submitForm}>Delete Freezer</Button>
    {#if selected != 0}
        <Button kind="danger-tertiary" iconDescription="Delete" icon={TrashCan} on:click={deleteTempData}>Delete Temperature Data</Button>
    {/if}
</div>
