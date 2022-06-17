<script>
    import { onMount } from "svelte";
    import { ExpandableTile } from "carbon-components-svelte";
    import FreezeList from "./FreezeList.svelte";
    import {arduinolist} from "./arduinolist"

    let arduino_data = [];
    onMount(async () => {
        arduino_data = await arduinolist()
    });
</script>

<div>
    {#each arduino_data as item}
	<div>
		<ExpandableTile>
            <div slot="above">
                <span>Arduino Name: {item.arduinoname}</span><br />
                <span>ID: {item.id}</span>
            </div>
            <div slot="below">
                <FreezeList ard_id = {item.id}/>
            </div>
        </ExpandableTile>
	</div>
    {/each}
</div>
