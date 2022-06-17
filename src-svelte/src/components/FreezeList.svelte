<script>
    import { onMount } from "svelte";
    import { ClickableTile } from "carbon-components-svelte";
    import { freezerList } from "./arduinolist";
    export let ard_id

    let freezer_data = [];
    onMount(async () => {
        freezer_data = await freezerList(ard_id);
    });
</script>

<div>
    {#each freezer_data as item}
            <ClickableTile href = {`/fridge/${item.id}`}>
                <span>Fridge Name: {item.name}</span><br />
                <span>Fridge ID:{item.id}</span>
            </ClickableTile>
    {/each}
</div>
