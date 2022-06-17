<script>
  import { Router } from "@roxi/routify";
  import { routes } from "../.routify/routes";
  import "carbon-components-svelte/css/all.css";
  import Layout from "./components/Layout.svelte"
</script>
<Layout>
  <Router {routes} />
</Layout>
