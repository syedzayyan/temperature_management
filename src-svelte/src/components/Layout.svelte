<script>
    import {
      Header,
      HeaderNav,
      HeaderNavItem,
      SkipToContent,
      Content,
      Grid,
      Row,
      Column,
    } from "carbon-components-svelte";
import Logout from "./Logout.svelte";
  
    let isSideNavOpen = false;
  </script>
  
  <Header company="WHRI" platformName="Temperature Sensor" bind:isSideNavOpen>
    <svelte:fragment slot="skip-to-content">
      <SkipToContent />
    </svelte:fragment>
    <HeaderNav>
      <HeaderNavItem href="/" text="Dashboard" />
      <HeaderNavItem href="/settings" text="Settings" />
      <HeaderNavItem href="/manual" text="Manual" />
    </HeaderNav>
    <HeaderNav>
      <Logout />
    </HeaderNav>
  </Header>
  
  <Content>
    <Grid>
      <Row>
        <Column>
          <slot></slot>
        </Column>
      </Row>
    </Grid>
  </Content>
  